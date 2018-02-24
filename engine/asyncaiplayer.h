#pragma once

#include "asyncplayer.h"
#include "aiplayer.h"
#include "chessboard.h"

class AsyncAiPlayer : public AsyncPlayer
{
public:
  AsyncAiPlayer(int color, int search_depth);

  virtual void asyncPrepare(const ChessBoard &board, ReadyHandler handler) override;
  virtual void asyncGetNext(const ChessBoard &board, MoveReadyHandler handler) override;
  virtual void asyncShowMove(const ChessBoard &board, const Move &move, ReadyHandler handler) override;
  virtual void asyncShowResult(const ChessBoard &board, EndStatus status, ReadyHandler handler) override;

  virtual void cancel() override;

private:
  AIPlayer m_ai_player;
};
