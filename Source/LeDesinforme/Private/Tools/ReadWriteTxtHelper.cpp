// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/ReadWriteTxtHelper.h"
#include "Containers/UnrealString.h"
#include <Runtime/Core/Public/Misc/Paths.h>
#include <Runtime/Core/Public/Misc/FileHelper.h>
#include <Runtime/Core/Public/HAL/PlatformFileManager.h>
#include <Runtime/Core/Public/HAL/FileManagerGeneric.h>
#include <Runtime/Core/Public/HAL/FileManager.h>
#include <Runtime/Renderer/Private/ShadingEnergyConservation.h>

TArray<FString> titleList;

FString UReadWriteTxtHelper::ReadTxt(FString FileName)
{
	FString resultString;

	FFileHelper::LoadFileToString(resultString, *(FPaths::ProjectContentDir() + "Txt/" + FileName));

	return resultString;
}

bool UReadWriteTxtHelper::WriteTxt(FString Text, FString FileName)
{
	bool result;

	result = FFileHelper::SaveStringToFile(Text, *(FPaths::ProjectContentDir() + "Txt/" + FileName));

	return result;
}

FString UReadWriteTxtHelper::ReadTrueSentences(FString directory)
{
    TArray<FString> files;
    directory += TEXT("True/");
    IFileManager& contentManager = IFileManager::Get();
    contentManager.FindFiles(files, *directory, TEXT("*.txt"));

    if (files.Num() == 0)
    {
        return FString();
    }

    int32 numSentences = FMath::RandRange(200, 500);
    FString combinedSentences;

    for (int32 i = 0; i < numSentences; ++i)
    {
        int32 randomFileIndex = FMath::RandRange(0, files.Num() - 1);
        FString selectedFilePath = directory + files[randomFileIndex];
        FString fileContent;

        if (FFileHelper::LoadFileToString(fileContent, *selectedFilePath))
        {
            TArray<FString> lines;
            fileContent.ParseIntoArrayLines(lines);

            if (lines.Num() > 0)
            {
                int32 randomLineIndex = FMath::RandRange(0, lines.Num() - 1);
                combinedSentences += lines[randomLineIndex].TrimStartAndEnd() + TEXT(" ");
            }
        }
    }

    return combinedSentences.TrimEnd();
}

FString UReadWriteTxtHelper::ReadFakeSentences(FString directory)
{
    TArray<FString> files;
    directory += TEXT("Fake/");
    IFileManager& contentManager = IFileManager::Get();
    contentManager.FindFiles(files, *directory, TEXT("*.txt"));

    if (files.Num() == 0)
    {
        return FString();
    }

    int32 numSentences = FMath::RandRange(200, 500);
    FString combinedSentences;

    for (int32 i = 0; i < numSentences; ++i)
    {
        int32 randomFileIndex = FMath::RandRange(0, files.Num() - 1);
        FString selectedFilePath = directory + files[randomFileIndex];
        FString fileContent;

        if (FFileHelper::LoadFileToString(fileContent, *selectedFilePath))
        {
            TArray<FString> lines;
            fileContent.ParseIntoArrayLines(lines);

            if (lines.Num() > 0)
            {
                int32 randomLineIndex = FMath::RandRange(0, lines.Num() - 1);
                combinedSentences += lines[randomLineIndex].TrimStartAndEnd() + TEXT(" ");
            }
        }
    }

    return combinedSentences.TrimEnd();
}

FString UReadWriteTxtHelper::MakeOINews(FString directory)
{
    TArray<FString> files;
    directory += TEXT("OI/");
    IFileManager& contentManager = IFileManager::Get();
    contentManager.FindFiles(files, *directory, TEXT("*.txt"));

    if (files.Num() == 0)
    {
        return FString();
    }

    int32 numSentences = FMath::RandRange(200, 500);
    FString combinedSentences;  

    for (int32 i = 0; i < numSentences; ++i)
    {
        int32 randomFileIndex = FMath::RandRange(0, files.Num() - 1);
        FString selectedFilePath = directory + files[randomFileIndex];
        FString fileContent;

        if (FFileHelper::LoadFileToString(fileContent, *selectedFilePath))
        {
            TArray<FString> lines;
            fileContent.ParseIntoArrayLines(lines);

            if (lines.Num() > 0)
            {
                int32 randomLineIndex = FMath::RandRange(0, lines.Num() - 1);
                combinedSentences += lines[randomLineIndex].TrimStartAndEnd() + TEXT(" ");
            }
        }
    }

    return combinedSentences.TrimEnd();
}

FNews UReadWriteTxtHelper::RandomRead(FString subject, ENewsType type)
{
    FNews resultNews;

    FString subjectName = ReadTxt("subjectNames.txt");

    TArray<FString> subjects;

    subjectName.ParseIntoArray(subjects, TEXT("\r\n"), true);

    FString sub = subjects[FMath::RandRange(0, subjects.Num() - 1)];
    FString Directory = FPaths::ProjectContentDir() + TEXT("Txt/") + sub + TEXT("/");
    TArray<FString> Files;
    IFileManager& FileManager = IFileManager::Get();
    FileManager.FindFiles(Files, *Directory, TEXT("*.txt"));

    if (Files.Num() == 0)
    {
        return FNews();
    }

    FString SelectedFile;

    switch (type)
    {
    case ENewsType::TrueNews:
        for (auto File : Files)
		{
			if (File.StartsWith("T"))
			{
                resultNews.bIsTrue = true;

                resultNews.newsType = ENewsType::TrueNews;

				SelectedFile = File;
				Files.Remove(File);
				break;
			}
		}
        break;
    case ENewsType::FakeNews:
        for (auto File : Files)
        {
            if (File.StartsWith("F"))
            {
                resultNews.bIsTrue = false;

                resultNews.newsType = ENewsType::FakeNews;

                SelectedFile = File;
                Files.Remove(File);
                break;
            }
        }
        break;
    case ENewsType::AINews:
        for (auto File : Files)
		{
			if (File.StartsWith("T"))
			{
				resultNews.bIsTrue = false;
                
				resultNews.newsType = ENewsType::AINews;

				SelectedFile = File;
				Files.Remove(File);
				break;
			}
		}
        break;
    case ENewsType::OINews:
        for (auto File : Files)
        {
            if (File.StartsWith("O"))
            {
                resultNews.bIsTrue = false;

                resultNews.newsType = ENewsType::OINews;

                SelectedFile = File;
                Files.Remove(File);
                break;
            }
        }
        break;
    default:
        for (auto File : Files)
        {
            if (File.StartsWith("T"))
            {
                resultNews.bIsTrue = true;

                resultNews.newsType = ENewsType::TrueNews;

                SelectedFile = File;
                Files.Remove(File);
                break;
            }
        }
        break;
    }

    FString FilePath = Directory + SelectedFile;
    FString FileContents;
    if (FFileHelper::LoadFileToString(FileContents, *FilePath))
    {
        TArray<FString> Lines;
        FileContents.ParseIntoArrayLines(Lines);

        if (Lines.Num() > 0)
        {
            resultNews.title = Lines[0].TrimStartAndEnd();
            titleList.Add(resultNews.title);

            if (resultNews.newsType == ENewsType::TrueNews)
            {
                resultNews.contents = ReadTrueSentences(Directory);
            }
            else if (resultNews.newsType == ENewsType::FakeNews)
            {
                resultNews.contents = ReadFakeSentences(Directory);
            }
            else if (resultNews.newsType == ENewsType::AINews)
            {
                resultNews.contents = ReadTrueSentences(Directory);
            }
            else if (resultNews.newsType == ENewsType::OINews)
            {
                resultNews.contents = MakeOINews(Directory);
            }
            
        }
    }

    return resultNews;
}

FString UReadWriteTxtHelper::ReadTitle(FString type)
{
	FString title;

	return title;
}

TArray<FString> UReadWriteTxtHelper::InputTitleList()
{
	TArray<FString> resultList;

	resultList = titleList;

	return resultList;
}

void UReadWriteTxtHelper::CleanTitleList()
{
	titleList.Empty();
}
