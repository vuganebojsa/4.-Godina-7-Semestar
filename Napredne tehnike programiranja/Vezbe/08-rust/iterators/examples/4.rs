// Popuni praznine i ispravi greške u kodu.
fn main() {
    let v1 = vec![1, 2, 3];

    let v1_iter = v1.iter();

    let total: i32 = v1_iter.sum();

    assert_eq!(total, 6);

    println!("{:?}",v1);
}