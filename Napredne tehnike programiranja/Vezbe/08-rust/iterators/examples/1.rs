// Popuni praznine.
fn main() {
    let v1 = vec![1, 2];
    let mut iter = v1.iter();
    assert_eq!(iter.next(), Some(&1));
    assert_eq!(iter.next(), Some(&2));
    assert_eq!(iter.next(), None);
}