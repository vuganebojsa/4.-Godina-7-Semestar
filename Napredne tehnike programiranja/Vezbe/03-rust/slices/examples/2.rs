// Ispravi greške u kodu
fn main() {
    let arr: [i32; 5] = [1, 2, 3, 4, 5];

    let slice: &[i32] = &arr[1..4]; // TODO
    assert_eq!(slice, &[2, 3, 4]);

    println!("Success!");
}
