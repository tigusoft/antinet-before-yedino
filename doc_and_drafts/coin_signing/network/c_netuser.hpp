#ifndef C_NETUSER_H
#define C_NETUSER_H

#include "../libs01.hpp"
#include "../c_user.hpp"
#include "c_TCPasync.hpp"

using namespace boost::asio;

class c_netuser final : public c_user {
  public:
    c_netuser (const std::string &username,			///< TODO need to set targer before use!
               unsigned short local_port = 30000);
    c_netuser (c_user &&user,						///< TODO need to set targer before use!
               unsigned short local_port = 30000);

    /// Send token to specific host target
    void send_token_bynet (const std::string &host, unsigned short server_port);
    unsigned int get_port();
    virtual ~c_netuser ();

  private:
//    friend class boost::serialization::access;
//    template <typename Archive>
//    void serialize (Archive &ar, const unsigned int version) {
//        UNUSED(version);
//        ar & boost::serialization::base_object<c_user>(*this);
//        ar & server_port;
//    }

    c_TCPasync m_TCPasync;
    void set_commands ();
    std::map<packet_type,std::shared_ptr<c_TCPcommand>> m_TCPcommands;
    std::atomic<bool> m_stop_thread;
    std::thread m_thread;

    void send_contract(const ed_key &recipient, c_contract contract);
    void check_inboxes ();
    void recieve_coin ();
    void recieve_contract ();
};

#endif // C_NETUSER_H
