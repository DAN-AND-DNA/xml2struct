#include "pugixml.hpp"
#include <stdint.h>

struct LuckyDraw {
    uint32_t PrizeID;  //奖品ID 
    uint32_t PrizeType;  //奖品类型 
    std::string PrizeName;  //奖品名称 
    float Probability;  //概率 
    uint32_t NumForSecKill;  //必中次数 
    uint32_t RewardPoints;  //积分奖励 

    LuckyDraw()
    {

        pugi::xml_document doc;
        if(!doc.load_file("LuckyDraw.xml")) exit(-1);
        pugi::xml_node stStructs = doc.child("LuckyDraw");
        for(pugi::xml_node_iterator it = stStructs.begin(); it != stStructs.end(); ++it)
        {
               PrizeID = static_cast<uint32_t>(atoi(it->attribute("PrizeID").value()));
               PrizeType = static_cast<uint32_t>(atoi(it->attribute("PrizeType").value()));
               PrizeName = it->attribute("PrizeName").value();
               Probability = atof(it->attribute("Probability").value());
               NumForSecKill = static_cast<uint32_t>(atoi(it->attribute("NumForSecKill").value()));
               RewardPoints = static_cast<uint32_t>(atoi(it->attribute("RewardPoints").value()));

        }
    }
};
