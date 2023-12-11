
struct Point<T>{
    x: T,
     y: T
}
struct Pointi<X1, Y1>{
    x: X1,
    y: Y1
}
impl<T> Point<T>{
    fn x(&self) -> &T{
        &self.x
    }
}
impl<X1, Y1> Pointi<X1, Y1>{
    fn mixup<X2, Y2>(self, other: Pointi<X2, Y2>) -> Pointi<X1, Y2>{
        Pointi{
            x: self.x,
            y: other.y
        }
    }
}
impl Point<f32>{
    fn distance_from_origin(&self) -> f32{
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}
fn main() {

    let p1 = Pointi{x: 5, y:10.4};
    let p2 = Pointi{x: "Hello", y:'c'};
    let p3 = p1.mixup(p2);
    println!("{} {}", p3.x, p3.y);

}
