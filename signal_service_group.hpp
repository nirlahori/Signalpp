#ifndef SIGNAL_SERVICE_GROUP_HPP
#define SIGNAL_SERVICE_GROUP_HPP

#include <vector>
#include <utility>
#include <algorithm>

#include "signal_service.hpp"


class Signal_Service_Group
{

    using signal_type = int;
    using service_type = Signal_Service;
    using service_group_type = std::vector<service_type>;
    using disposition_type = void(*)();
    using service_pack_type = std::pair<service_type, disposition_type>;

    std::vector<service_pack_type> serv_grp;


    std::vector<disposition_type> _in_get_service_disposition(const int& signal){
        std::vector<disposition_type> dsp_vec;
        std::for_each(serv_grp.begin(), serv_grp.end(), [&](const service_pack_type& elem){
            if(elem.first.check_signal(signal)){
                dsp_vec.push_back(elem.second);
            }
        });
        return dsp_vec;
    }



public:

    Signal_Service_Group() = default;

    Signal_Service_Group(const std::vector<service_pack_type>& _serv_grp) :
        serv_grp (_serv_grp)
    {}

    void invoke_service_disposition(const signal_type& signal){
        std::vector<disposition_type> invoke_vec {_in_get_service_disposition(signal)};
        std::for_each(invoke_vec.begin(), invoke_vec.end(), [](disposition_type sig_disp){
            sig_disp();
        });
    }

    void add_service(const service_type& serv, disposition_type&& func){
        serv_grp.push_back(std::make_pair(serv, std::move(func)));
    }
};

#endif // SIGNAL_SERVICE_GROUP_HPP
