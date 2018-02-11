#include "asyncgame.h"

#include "chessboard.h"

AsyncGame::AsyncGame(std::shared_ptr<io_service> io_ptr,
                     TAsyncPlayerPtr p1,
                     TAsyncPlayerPtr p2)
    : m_io_ptr(io_ptr),
      m_player1(p1),
      m_player2(p2),
      m_end_status(AsyncPlayer::EndStatus::NONE)
{
}

void AsyncGame::start(std::function<void(AsyncPlayer::EndStatus end_status)> end_game_handler)
{
  ChessBoard board;
  board.initDefaultSetup();

  std::shared_ptr<io_service::strand> strand_ptr = std::make_shared<io_service::strand>(*m_io_ptr);
  m_player1->setStrand(strand_ptr);
  m_player2->setStrand(strand_ptr);

  m_player1->asyncPrepare(board, [] { /* PREPARED */ });
  m_player2->asyncPrepare(board, [] { /* PREPARED */ });
  do_move(board);
  end_game_handler(m_end_status);
}

void AsyncGame::do_move(ChessBoard &board)
{
  m_player1->asyncGetNext(board, [this, &board](const Move &move) {
    board.move(move);
    board.print(move);
    m_player2->asyncShowMove(board, move, [this, &board] {
      auto status = board.getPlayerStatus(m_player2->getColor());
      if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
      {
        std::swap(m_player1, m_player2);
        do_move(board);
      }
      switch (status)
      {
      case ChessPlayer::Checkmate:
        m_end_status = board.next_move_color == WHITE ? AsyncPlayer::EndStatus::WHITE_LOOSE : AsyncPlayer::EndStatus::WHITE_WIN;
        break;
      case ChessPlayer::Draw:
        m_end_status = AsyncPlayer::EndStatus::DRAW;
        break;
      default:
        break;
      }
    });
  });
}