// Popuni prazninu i ispravi greške u kodu.
#[derive(Debug)]
#[derive(PartialEq)]
enum IpAddr {
    V4(String),
    V6(String),
}
fn main() {
    let mut v : Vec<IpAddr>= Vec::new();
    v.push(IpAddr::V4(String::from("127.0.0.1")));
    v.push(IpAddr::V6(String::from("::1")));
    println!("{:?}", v);
    assert_eq!(v[0], IpAddr::V4("127.0.0.1".to_string()));
    assert_eq!(v[1], IpAddr::V6("::1".to_string()));

    println!("Success!");
}
