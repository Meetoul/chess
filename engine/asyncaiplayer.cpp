#include "asyncaiplayer.h"

using namespace std;

AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth)
    : AsyncPlayer(color), m_ai_player(color, search_depth) {}

void AsyncAiPlayer::asyncPrepare(const ChessBoard &board, ReadyHandler handler)
{
    handler();
}

void AsyncAiPlayer::asyncGetNext(const ChessBoard &orig_board, MoveReadyHandler handler) {}
void AsyncAiPlayer::asyncShowMove(const ChessBoard &board, const Move &move, ReadyHandler handler) {}
void AsyncAiPlayer::asyncShowResult(const ChessBoard &board, EndStatus status, ReadyHandler handler) {}

void AsyncAiPlayer::cancel() {}
