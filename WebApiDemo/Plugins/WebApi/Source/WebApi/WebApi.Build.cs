using UnrealBuildTool;

public class WebApi : ModuleRules
{
	public WebApi(TargetInfo Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				"WebApi/Public",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"WebApi/Private",
				"WebApi/Private/ThirdParty/liboauthcpp",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "HTTP",
                "Json",
			}
		);

		if (Target.Type != TargetRules.TargetType.Server)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Slate",
					"SlateCore",
				}
			);
		}
	}
}
