pub mod containers;
pub mod exceptions;
pub mod extern_function;

use crate::extern_function::{
    OgCrCreateElectromagneticDotTimer, OgCrDestoryElectromagneticDotTimer,
    OgCrElectromagneticDotTimerPullTask, OgCrElectromagneticDotTimerSkipATimeStamp,
};
pub struct ElectromagneticDotTimer {
    pub value: extern_function::PtrElectromagneticDotTimer,
}
impl ElectromagneticDotTimer {
    pub fn new(frequency: i8) -> Option<Self> {
        let ptr = unsafe { OgCrCreateElectromagneticDotTimer(frequency) };
        if !ptr.is_null() {
            Some(ElectromagneticDotTimer { value: ptr })
        } else {
            None
        }
    }
    pub fn pull_task(&self) -> i64 {
        unsafe { OgCrElectromagneticDotTimerPullTask(self.value) }
    }
    pub fn skip_a_time_stamp(&mut self) {
        unsafe {
            OgCrElectromagneticDotTimerSkipATimeStamp(self.value);
        }
    }
}
impl Drop for ElectromagneticDotTimer {
    fn drop(&mut self) {
        unsafe {
            OgCrDestoryElectromagneticDotTimer(self.value);
        }
    }
}
