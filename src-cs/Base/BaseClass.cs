using System.Runtime.InteropServices;

namespace Base
{
    public static class Test
    {
        [UnmanagedCallersOnly(EntryPoint = "Add")]
        public static Int64 Add(Int64 lsh,Int64 rsh)
        {
            return lsh + rsh;
        }
    }
}

