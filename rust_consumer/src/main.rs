use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_int, c_void};

#[repr(C)]
pub struct TaskManagerC { _private: [u8; 0] }

extern "C" {
    fn taskmgr_create() -> *mut TaskManagerC;
    fn taskmgr_destroy(m: *mut TaskManagerC);
    fn taskmgr_add(m: *mut TaskManagerC, title: *const c_char, priority: c_int) -> c_int;
    fn taskmgr_mark_done(m: *mut TaskManagerC, id: c_int) -> c_int;
    fn taskmgr_remove_completed(m: *mut TaskManagerC);
    fn taskmgr_sort_by_priority(m: *mut TaskManagerC);
    fn taskmgr_list(m: *mut TaskManagerC) -> *mut c_char;
}

fn main() {
    unsafe {
        let mgr = taskmgr_create();
        if mgr.is_null() {
            eprintln!("Failed to create TaskManager");
            std::process::exit(1);
        }

        let make = |s: &str| CString::new(s).unwrap();

        let _ = taskmgr_add(mgr, make("Write proposal").as_ptr(), 2);
        let _ = taskmgr_add(mgr, make("Buy groceries").as_ptr(), 5);
        let _ = taskmgr_add(mgr, make("Fix bug #123").as_ptr(), 1);
        let _ = taskmgr_add(mgr, make("Read book").as_ptr(), 8);

        println!("All tasks:");
        let p = taskmgr_list(mgr);
        if !p.is_null() {
            let s = CStr::from_ptr(p).to_string_lossy();
            print!("{}", s);
            // free the buffer allocated in C
            libc::free(p as *mut c_void);
        }

        taskmgr_sort_by_priority(mgr);
        println!("\nSorted by priority:");
        let p = taskmgr_list(mgr);
        if !p.is_null() {
            let s = CStr::from_ptr(p).to_string_lossy();
            print!("{}", s);
            libc::free(p as *mut c_void);
        }

        let _ = taskmgr_mark_done(mgr, 3);
        println!("\nAfter marking task 3 done:");
        let p = taskmgr_list(mgr);
        if !p.is_null() {
            let s = CStr::from_ptr(p).to_string_lossy();
            print!("{}", s);
            libc::free(p as *mut c_void);
        }

        taskmgr_remove_completed(mgr);
        println!("\nAfter removing completed tasks:");
        let p = taskmgr_list(mgr);
        if !p.is_null() {
            let s = CStr::from_ptr(p).to_string_lossy();
            print!("{}", s);
            libc::free(p as *mut c_void);
        }

        taskmgr_destroy(mgr);
    }
}
