using System;
using System.IO;
using UnrealBuildTool;

public class OpenSLL : ModuleRules
{
	public OpenSLL(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "OpenSSL", "lib", "openssl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "OpenSSL", "lib", "libssl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "OpenSSL", "lib", "libcrypto.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("libcrypto-3-x64.dll");
			PublicDelayLoadDLLs.Add("libssl-3-x64.dll");

			// Ensure that the DLL is staged along with the executable
			String P1 = Path.Combine(ModuleDirectory, "OpenSSL", "bin", "libcrypto-3-x64.dll");
			String P2 = Path.Combine(ModuleDirectory, "OpenSSL", "bin", "libssl-3-x64.dll");

			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/OpenSSL/Win64/libcrypto-3-x64.dll", P1);
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/OpenSSL/Win64/libssl-3-x64.dll", P2);
		}
	}
}