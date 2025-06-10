#ifndef SIGNAL_MANAGER_HPP
#define SIGNAL_MANAGER_HPP

#include <csignal>
#include <stop_token>
#include "signal_service_group.hpp"
#include "internal/sigset_impl.hpp"



class Signal_Manager
{

    using signal_type = int;
    using signal_set_type = sigset_t;

    Signal_Service_Group sig_grp;
    SigSet sig_set;
    std::stop_source thr_stop_src;
    std::stop_token thr_stop_tok;



public:

    Signal_Manager() :
        thr_stop_src {std::stop_source()},
        thr_stop_tok {thr_stop_src.get_token()}
    {}

    Signal_Manager(const Signal_Service_Group& _group, const signal_set_type* _set) :
        sig_grp{_group},
        sig_set{_set},
        thr_stop_src {std::stop_source()},
        thr_stop_tok {thr_stop_src.get_token()}
    {}

    Signal_Manager(Signal_Service_Group&& _group, const signal_set_type* _set) :
        sig_grp {std::move(_group)},
        sig_set {_set},
        thr_stop_src {std::stop_source()},
        thr_stop_tok {thr_stop_src.get_token()}
    {}

    void start_thread(){

        siginfo_t recvinfo;

        while(!thr_stop_tok.stop_requested()){
            int recv_sig = sigwaitinfo(sig_set.get_native_handle(), &recvinfo);
            sig_grp.invoke_service_disposition(recv_sig);
        }
    }

    void stop_thread(){
        thr_stop_src.request_stop();
    }
};

#endif // SIGNAL_MANAGER_HPP
