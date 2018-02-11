#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <functional>

#include "global.h"
#include "asyncaiplayer.h"

using namespace boost::asio;

class AsyncGame
{
public:
  AsyncGame(std::shared_ptr<io_service> io_ptr,
            TAsyncPlayerPtr p1,
            TAsyncPlayerPtr p2);

  void start(std::function<void(AsyncPlayer::EndStatus end_status)>);

private:
  std::shared_ptr<io_service> m_io_ptr;
  TAsyncPlayerPtr m_player1;
  TAsyncPlayerPtr m_player2;
  AsyncPlayer::EndStatus m_end_status;

  void do_move(ChessBoard &board);
};