#include "../conutils/cursor.hpp"
#include "../statemanager.hpp"
#include "../states/gameoverstate.hpp"
#include <cassert>
#include <cstdio>
#include "player.hpp"

namespace Entity
{
	unsigned const autodropIntervalInMs = 300;

	void Player::DrawScore() const
	{
		Color::Set(Color::Color());
		Cursor::Set(scorePosition);

		std::printf("%05u", score); // Oh boy, we're mixing with C libs now
	}

	void Player::CalculateScore(unsigned const rowsPopped)
	{
		if (rowsPopped == 0)
			return;

		score += rowsPopped * 125;
		DrawScore();
	}

	void Player::ClearPreviewArea() const
	{
		Color::Set(Color::Color());
		for (SHORT y = 0; y < 4; ++y)
		{
			Cursor::Set(COORD{ previewSpawnPosition.X, previewSpawnPosition.Y + y });
			std::printf("    ");
		}
	}

	void Player::CycleTetromino()
	{
		Color::Set(Color::Color());
		auto const previewblocks = previewTetroPtr->GetState().GetTranslatedBlocks();
		for (auto const& b : previewblocks)
		{
			Cursor::Set(b);
			std::cout << ' ';
		}

		currentTetroPtr.swap(previewTetroPtr);
		currentTetroPtr->SetPosition(spawnPosition);
		currentTetroPtr->Draw();

		previewTetroPtr = tetrominoFactory.GetRandomTetromino(previewSpawnPosition);
		previewTetroPtr->Draw();

		if (field.IsColliding(currentTetroPtr->GetState().GetTranslatedBlocks()))
		{
			auto& stManager = StateManager::GetInstance();
			stManager.PopState();
			stManager.PushState(std::make_unique<GameOverState>());
			return;
		}
	}

	bool Player::HandleInput()
	{
		assert(currentTetroPtr != nullptr);

		EventHandler const& evHandler = EventHandler::GetInstance();
		if (evHandler.WasActionReleased(PlayerActions::RotateLeft))
		{
			currentTetroPtr->RotateLeft();
		}
		else if (evHandler.WasActionReleased(PlayerActions::RotateRight))
		{
			currentTetroPtr->RotateRight();
		}

		SHORT X_movement = 0;
		if (evHandler.WasActionReleased(PlayerActions::MoveLeft))
		{
			X_movement -= 1;
		}
		else if (evHandler.WasActionReleased(PlayerActions::MoveRight))
		{
			X_movement += 1;
		}

		currentTetroPtr->Move(X_movement);

		if (evHandler.WasActionPressed(PlayerActions::MoveDown))
		{
			return true;
		}

		return false;
	}

	void Player::Update(unsigned const elapsedMs)
	{
		bool drop = false;

		autoDropElapsedTime += elapsedMs;
		if (autoDropElapsedTime >= autodropIntervalInMs)
		{
			drop = true;
			autoDropElapsedTime = 0U;
		}

		TetrominoState const currentState = currentTetroPtr->GetState();
		drop = drop || HandleInput();

		TetrominoState candidateState = currentTetroPtr->GetState();
		if (drop)
		{
			candidateState.position.Y += 1;
			if (field.IsColliding(candidateState.GetTranslatedBlocks()))
			{
				// Illegal move ?
				candidateState.position.Y -= 1;
				if (field.IsColliding(candidateState.GetTranslatedBlocks()))
				{
					candidateState = currentState;

					candidateState.position.Y += 1;
					if (field.IsColliding(candidateState.GetTranslatedBlocks()))
					{
						unsigned const rowsPopped = field.Merge(currentState.GetTranslatedBlocks());
						CalculateScore(rowsPopped);
						CycleTetromino();
						return;
					}
				}
				else
				{
					unsigned const rowsPopped = field.Merge(candidateState.GetTranslatedBlocks());
					CalculateScore(rowsPopped);
					CycleTetromino();
					return;
				}
			}
		}
		else
		{
			if (field.IsColliding(candidateState.GetTranslatedBlocks()))
			{
				// Illegal move
				candidateState = currentState;
			}
		}

		currentTetroPtr->SetState(candidateState);

		if (drop || currentState != candidateState)
		{
			currentState.Draw(Color::Color(), ' ');
			currentTetroPtr->Draw();
		}
	}

	Player::Player(COORD const _previewSpawnPosition,
		COORD const _scorePosition,
		Field& _field)
		: spawnPosition({ _field.GetPosition().X + _field.GetSize().X / 2, _field.GetPosition().Y }),
		previewSpawnPosition(_previewSpawnPosition),
		scorePosition(_scorePosition),
		field(_field),
		tetrominoFactory(1337),
		autoDropElapsedTime(0U),
		score(0U)
	{
		ClearPreviewArea();
		DrawScore();
		previewTetroPtr = tetrominoFactory.GetRandomTetromino(spawnPosition);
		CycleTetromino();
	}
}
