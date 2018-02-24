#include "asyncgame.h"

namespace ph = std::placeholders;

AsyncGame::AsyncGame(const std::shared_ptr<io_service> &io_ptr,
                     TAsyncPlayerPtr p1,
                     TAsyncPlayerPtr p2)
    : m_io_ptr(io_ptr),
      m_player1(p1),
      m_player2(p2),
      m_board()
{
  m_board.initDefaultSetup();

  m_strand_ptr = std::make_shared<io_service::strand>(*m_io_ptr);

  m_player1->setStrand(m_strand_ptr);
  m_player2->setStrand(m_strand_ptr);

  m_player1->setService(m_io_ptr);
  m_player2->setService(m_io_ptr);
}

void AsyncGame::start(EndGameHandler end_game_handler)
{
  m_end_game_handler_ptr = std::make_shared<EndGameHandler>(end_game_handler);
  m_player1->asyncPrepare(m_board, [] { /* PREPARED */ });
  m_player2->asyncPrepare(m_board, [] { /* PREPARED */ });

  m_player1->asyncGetNext(m_board, std::bind(&AsyncGame::get_next_handler, this, ph::_1));
}

void AsyncGame::get_next_handler(const Move &move)
{
  m_board.move(move);
  m_board.print(move);
  m_player2->asyncShowMove(m_board, move, std::bind(&AsyncGame::show_move_handler, this));
}

void AsyncGame::show_move_handler()
{
  auto status = m_board.getPlayerStatus(m_player2->getColor());
  if (status == ChessPlayer::Normal || status == ChessPlayer::InCheck)
  {
    std::swap(m_player1, m_player2);
    m_player1->asyncGetNext(m_board, std::bind(&AsyncGame::get_next_handler, this, ph::_1));
  }
  else
  {
    AsyncPlayer::EndStatus end_status;
    switch (status)
    {
    case ChessPlayer::Checkmate:
      if (m_board.next_move_color == WHITE)
        end_status = AsyncPlayer::WHITE_LOOSE;
      else
        end_status = AsyncPlayer::EndStatus::WHITE_WIN;
      break;
    case ChessPlayer::Draw:
      end_status = AsyncPlayer::EndStatus::DRAW;
      break;
    default:
      break;
    }
    m_end_game_handler_ptr->operator()(end_status);
  }
}
