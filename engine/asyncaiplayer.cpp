#include "asyncaiplayer.h"
#include "chessboard.h"
#include <boost/asio.hpp>

using namespace std;

AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth)
    : AsyncPlayer(color), m_ai_player(color, search_depth) {}

void AsyncAiPlayer::asyncPrepare(const ChessBoard &board, ReadyHandler handler)
{
    m_strand_ptr->post(handler);
}

void AsyncAiPlayer::asyncGetNext(const ChessBoard &board, MoveReadyHandler handler)
{
    auto get_move = [this, &board, handler] {
        Move move;
        m_ai_player.getMove(board, move);
        m_strand_ptr->post([move, handler] { handler(move); });
    };
    m_strand_ptr->post(get_move);
}

void AsyncAiPlayer::asyncShowMove(const ChessBoard &board, const Move &move, ReadyHandler handler)
{
    auto show_move = [this, &board, &move, handler] {
        m_ai_player.showMove(board, const_cast<Move &>(move));
        m_strand_ptr->post([handler] { handler(); });
    };
    m_strand_ptr->post(show_move);
}

void AsyncAiPlayer::asyncShowResult(const ChessBoard &board, EndStatus status, ReadyHandler handler)
{
    m_strand_ptr->post(handler);
}

void AsyncAiPlayer::cancel()
{
}
