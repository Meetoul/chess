#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <functional>

#include "global.h"
#include "asyncaiplayer.h"
#include "chessboard.h"

using namespace boost::asio;

typedef std::function<void(AsyncPlayer::EndStatus end_status)> EndGameHandler;

class AsyncGame
{
public:
  AsyncGame(std::shared_ptr<io_service> io_ptr,
            TAsyncPlayerPtr p1,
            TAsyncPlayerPtr p2);

  void start(EndGameHandler end_game_handler);

private:
  std::shared_ptr<io_service::strand> m_strand_ptr;

  TAsyncPlayerPtr m_player1;
  TAsyncPlayerPtr m_player2;

  EndGameHandler m_end_game_handler;

  ChessBoard m_board;

  void get_next_handler(const Move &move);
  void show_move_handler();
};