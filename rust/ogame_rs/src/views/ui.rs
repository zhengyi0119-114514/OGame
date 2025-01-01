use crate::modules::math::{Point, Rectangle};
pub trait DisplayAbleObject {
    fn Display()->bool;
}
pub struct Button {
    pub p: Point,
    pub size: Rectangle,
    pub label: String,
}

