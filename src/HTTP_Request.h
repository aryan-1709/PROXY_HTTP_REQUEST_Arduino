#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include<string>

using namespace std;

class http_request {
private:
    string target_host="";
    string target_path="";
public:
    http_request(string  target_host, string target_path){
        this->target_host = target_host;
        this->target_path = target_path;
    }

    string get_target_path(){
        if(this->target_path=="")  return "No target_path given";
        return this->target_path;
    }
    string get_target_host(){
        if(this->target_host=="")  return "No target_host given";
        return this->target_host;
    }

    void set_target_path(string target_path){
        this->target_path = target_path;
    }
    void set_target_host(string target_host){
        this->target_host = target_host;
    }

    virtual string get_request(){};
};

#endif