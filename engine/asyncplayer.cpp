#include "asyncplayer.h"

AsyncPlayer::AsyncPlayer(int color):
    color(color)
{

}

AsyncPlayer::~AsyncPlayer()
{

}

int AsyncPlayer::getColor() const
{
    return color;
}

void AsyncPlayer::setColor(int value)
{
    color = value;
}

std::shared_ptr<boost::asio::io_service::strand> AsyncPlayer::getStrand() const
{
    return m_strand_ptr;
}

void AsyncPlayer::setStrand(const std::shared_ptr<boost::asio::io_service::strand> &value)
{
    m_strand_ptr = value;
}

void AsyncPlayer::setService(const std::shared_ptr<boost::asio::io_service> &io_serv)
{
    m_io_service = io_serv;
}