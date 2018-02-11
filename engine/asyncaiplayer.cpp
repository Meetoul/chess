#include "asyncaiplayer.h"
#include "chessboard.h"

using namespace std;

AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth)
    : AsyncPlayer(color), m_ai_player(color, search_depth) {}

void AsyncAiPlayer::asyncPrepare(const ChessBoard &board, ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::asyncGetNext(const ChessBoard &board, MoveReadyHandler handler)
{
    Move move;
    m_ai_player.getMove(board, move);
    handler(move);
}
void AsyncAiPlayer::asyncShowMove(const ChessBoard &board, const Move &move, ReadyHandler handler)
{
    m_ai_player.showMove(board, const_cast<Move &>(move));
    handler();
}
void AsyncAiPlayer::asyncShowResult(const ChessBoard &board, EndStatus status, ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::cancel()
{
}
