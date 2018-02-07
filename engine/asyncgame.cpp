#include "asyncgame.h"

#include "chessboard.h"

AsyncGame::AsyncGame(std::shared_ptr<io_service> io_ptr,
                     TAsyncPlayerPtr p1,
                     TAsyncPlayerPtr p2)
    : m_io_ptr(io_ptr),
      m_player1(p1),
      m_player2(p2)
{
}

void AsyncGame::start(std::function<void(AsyncPlayer::EndStatus end_status)>)
{
  ChessBoard board;
  board.initDefaultSetup();

  m_player1->asyncPrepare(board, [] {});
  m_player2->asyncPrepare(board, [] {});

  AsyncPlayer::EndStatus status = AsyncPlayer::EndStatus::NONE;
  while (AsyncPlayer::EndStatus::NONE == status)
  {
    Move move;

    m_player1->asyncGetNext(board, [&move](Move mv) {
      move = mv;
    });

    board.move(move);

    m_player2->asyncShowMove(board, move, [] {});
    board.print(move);

    std::swap(m_player1, m_player2);

    int figures_count = board.get_all_figures_count();
    board.refreshFigures();
    if (board.get_all_figures_count() != figures_count)
    {
      break;
    }
  }
}