use std::pin::Pin;

#[repr(C)]
struct Package<'arr_life> {
    u_sixty_four: u64, // 8 byte
    s_sixty_four: i64, // 8 byte
    u_thirty_two: u32, // 4 byte
    s_thirty_two: i32, // 4 byte
    u_sixteen: u16,   // 2 byte
    s_sixteen: i16,   // 2 byte
    u_eight: u8,      // 1 byte
    s_eight: i8,      // 1 byte
    arr_ptr: &'arr_life mut [[i8; 2]; 2],
}

impl<'arr_life> Package<'arr_life> {
    #[inline]
    pub fn mutate_package(&mut self) {
        self.u_eight *= 2;
        self.u_sixteen *= 2;
        self.u_thirty_two *= 2;
        self.u_sixty_four *= 2;
        self.s_eight *= 2;
        self.s_sixteen *= 2;
        self.s_thirty_two *= 2;
        self.s_sixty_four *= 2;
        // for simplicity let mutate single element of slice
        self.arr_ptr[0][0] += 10;
    }
}

#[cxx::bridge]
mod ffi {

    #[namespace = "perf"]
    unsafe extern "C++" {
        include!("header.h");
        type Package;
        fn new_package() -> UniquePtr<Package>;
        fn get_a_mutable_pointer(self: Pin<&mut Package>) -> *mut i8;
    }

    #[namespace = "ruster_space"]
    extern "Rust" {
        unsafe fn mutate(pack: *mut Package);
        pub fn demonstrate_pinned() -> *mut i8;
    }
}

pub unsafe fn mutate(pack: *mut ffi::Package) {
    let rust_pack = pack as *mut Package;
    (*rust_pack).mutate_package();
}

pub fn demonstrate_pinned() -> *mut i8 {
    let mut pack = unsafe { Pin::from(Box::from_raw(ffi::new_package().into_raw())) };
    pack.as_mut().get_a_mutable_pointer()
}

#[cfg(test)]
mod tests {
    // use super::*;

    #[test]
    fn it_works() {}
}
