// Ispravi grešku u kodu i popuni praznine.
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);
fn main() {
    let v = Color(0, 127, 255);
    check_color(v);

    println!("Success!");
}   

fn check_color(p: Color) {
    let Color(x, y, z) = p;
    assert_eq!(x, 0);
    assert_eq!(y, 127);
    assert_eq!(z, 255);
 }