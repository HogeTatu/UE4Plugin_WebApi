// Some copyright should be here...

using UnrealBuildTool;

public class WebApi : ModuleRules
{
	public WebApi(TargetInfo Target)
	{

		PublicIncludePaths.AddRange(
			new string[] {
				"WebApi/Public",
				"WebApi/Public/Api",
				"WebApi/Public/Filter",
				"WebApi/Public/RequestBody",
				"WebApi/Public/ResponseBody",
			}
		);


		PrivateIncludePaths.AddRange(
			new string[] {
				"WebApi/Private",
				"WebApi/Private/Api",
				"WebApi/Private/Filter",
				"WebApi/Private/RequestBody",
				"WebApi/Private/ResponseBody",
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "HTTP",
				"CoreUObject",
				"Engine",
                "Json",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
