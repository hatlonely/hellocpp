namespace cpp addservice

struct Request {
    1: i64 a;
    2: i64 b;
}

struct Response {
    1: i64 v;
    2: string err;
}

service Service {
    Response add(1: Request request);
}
