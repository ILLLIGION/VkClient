#include <string>
#include "json.hpp"

struct VkFriend
{
	using json = nlohmann::json;
	VkFriend() : id("unknown"), fname("unknown"), lname("unknown"), bdate("unknown"), online("unknown") {};
	VkFriend(json jsn_id, json jsn_fname, json jsn_lname, json jsn_bdate, json jsn_online) : id(jsn_id), fname(jsn_fname), lname(jsn_lname), bdate(jsn_bdate), online(jsn_online) {};
	json id;
	json fname;
	json lname;
	json bdate;
	json online;
	friend auto operator == (const VkFriend some_friend, const VkFriend another_friend) -> bool
	{
		if (some_friend.id == another_friend.id && some_friend.fname == another_friend.fname && some_friend.lname == another_friend.lname && some_friend.bdate == another_friend.bdate && some_friend.online == another_friend.online) return true;
		else return false;
	}
	auto PrintFriend () -> void
	{
		std::cout << "id:" << id.begin().value() << " First name:" << fname.begin().value() << " Last Name" << lname.begin().value() << " Birthday:" << bdate.begin().value() << " Online:" << online.begin().value() << std::endl;
	}
	~VkFriend() {};
};
