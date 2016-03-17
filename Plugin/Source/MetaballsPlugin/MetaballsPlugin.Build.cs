using UnrealBuildTool;
using System.IO;

public class MetaballsPlugin : ModuleRules
{

    public MetaballsPlugin(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(new string[] { "MetaballsPlugin/Private" });
	PublicIncludePaths.AddRange(new string[] { "MetaballsPlugin/Public" });

        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "ProceduralMeshComponent" });
    }
}