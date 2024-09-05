// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectURServerTarget : TargetRules
{
	public ProjectURServerTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.Add("ProjectUR"); //이 행은 프로젝트 이름에 맞게 변경합니다.
    }
}
