using UnrealBuildTool;

public class u04_ThirdPersonCPP : ModuleRules
{
	public u04_ThirdPersonCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.Add(ModuleDirectory);

	}
}
