// Popuni praznine
fn main() {  
    let mut s = String::from("hello, world");
 
    let slice1: &str = &s[..];
    assert_eq!(slice1, "hello, world");
 
    let slice2 = &s[0..5];
    assert_eq!(slice2, "hello");
 
    let mut slice3: String = (&s[..]).to_string(); 
    slice3.push('!');
    assert_eq!(slice3, "hello, world!");
 
    println!("Success!");
 }
 