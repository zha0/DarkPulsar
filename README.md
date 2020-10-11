# Timeline

 - **[10/09/2020]**: Wrote the project template for DarkPulsar to use the method that the original sample abused to intercept SpAcceptLsaModeContext: After performing a minor amount of RE against lsasrv.dll ( the core DLL of Lsa I guess? ), I saw  that it was allocating a heap pointer to store the table returned from SpLsaModeInitialize(). This table was then referenced thereon whenever something like NTLMSSP was requested as a authentication mechanism. Additionally, it was allocated on top of the default Process Heap. Therein, by walking the heap using the HeapWalk() API I was able to find the page containing the SECPKG_FUNCTION_TABLE structure, based on the exported SpInitialize() export.

# Ideas
 - **IDEA 1**: Create an custom protocol to communicate with the client over the authentication mechanisms. The original did this, with some weird encryption. If we opt for this, I say we try using chacha20, it seems pretty minimal and stable.
 - **IDEA 2**: Possibly create a minimal COFF Object Linker? Like how Cobalt Strike does for BOF's. Hrm.
