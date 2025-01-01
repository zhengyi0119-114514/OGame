pub trait Shape {}
pub struct Point {
    pub x: i32,
    pub y: i32,
}
impl Clone for Point {
    fn clone(&self) -> Self {
        Self {
            x: self.x.clone(),
            y: self.y.clone(),
        }
    }
}
pub struct Circle {
    pub center: Point,
    pub radius: i32,
}
impl Circle {
    pub fn new(p: &Point, radius: i32) -> Circle {
        return Circle {
            center: p.clone(),
            radius,
        };
    }
    pub fn is_in(&self, p: &Point) -> bool {
        return f64::sqrt(((self.center.x - p.x).pow(2) + (self.center.y - p.y).pow(2)).into())
            <= self.radius.into();
    }
}
impl Clone for Circle {
    fn clone(&self) -> Self {
        Self {
            center: self.center.clone(),
            radius: self.radius.clone(),
        }
    }
}

pub struct Rectangle {
    pub weight: i32,
    pub height: i32,
}
impl Rectangle {
    pub fn new(weight: i32, height: i32) -> Self {
        return Rectangle { weight, height };
    }
}
impl Clone for Rectangle {
    fn clone(&self) -> Self {
        Self {
            weight: self.weight.clone(),
            height: self.height.clone(),
        }
    }
}
pub struct LinearFunctions {}
