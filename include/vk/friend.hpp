#include <string>
#include "json.hpp"

struct VkFriend
{
	using json = nlohmann::json;
	VkFriend(json jsn_id, json jsn_fname, json jsn_lname, json jsn_bdate, json jsn_online) : id(jsn_id), fname(jsn_fname), lname(jsn_lname), bdate(jsn_bdate), online(jsn_online) {};
	json id;
	json fname;
	json lname;
	json bdate;
	json online;
	auto PrintFriend () -> void
	{
		std::cout << "id:" << id.begin().value() << " First name:" << fname.begin().value() << " Last Name" << lname.begin().value() << " Birthday:" << bdate.begin().value() << " Online:" << online.begin().value() << std::endl;
	}
	~VkFriend();
};
