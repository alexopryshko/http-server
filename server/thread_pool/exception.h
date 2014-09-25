class bad_request : public std::exception {
public:
    bad_request() {};
    ~bad_request() throw() {};
};

class not_found : public std::exception {
public:
    not_found() {};
    ~not_found() throw() {};
};