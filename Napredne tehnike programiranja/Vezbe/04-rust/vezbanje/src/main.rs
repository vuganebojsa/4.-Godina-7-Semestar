struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
  }

  fn build_user(email: String, username: String) -> User {
      User {
          active: true,
          username,
          email,
          sign_in_count: 1,
      }
}
#[derive(Debug)]
struct Rectangle{
    width: u32,
    height: u32
}
impl Rectangle{
    fn area(&self) -> u32{
        self.width * self.height
    }
    fn can_hold(&self, other: &Rectangle) -> bool{
        self.width > other.width && self.height > other.height
    }
    fn square(size: u32) -> Rectangle{
        Rectangle{
            width: size,
            height: size
        }
    }
}

fn main() {
   let rect = Rectangle{
    width: 30,
     height: 50
   };
   println!("The area of rect is: {}", area(&rect));
   println!("Rect is {:?}", rect.area());
   let squ = Rectangle::square(32);
   println!("Square is {:?}", squ);
}

fn area(rectangle: &Rectangle) -> u32{
    rectangle.width * rectangle.height
}
