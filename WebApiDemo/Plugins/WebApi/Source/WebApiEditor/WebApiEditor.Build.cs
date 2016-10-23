// Some copyright should be here...

using UnrealBuildTool;

public class WebApiEditor : ModuleRules
{
	public WebApiEditor(TargetInfo Target)
	{

		PublicIncludePaths.AddRange(
			new string[] {
				"WebApiEditor/Public",
				"WebApiEditor/Public/Nodes",
			}
		);


		PrivateIncludePaths.AddRange(
			new string[] {
				"WebApiEditor/Private",
				"WebApiEditor/Private/Nodes",
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "InputCore",
				"Slate",
                "EditorStyle",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"EditorStyle",
                "KismetCompiler",
				"UnrealEd",
                "GraphEditor",
				"SlateCore",
                "Kismet",
                "BlueprintGraph",
                "WebApi",
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
