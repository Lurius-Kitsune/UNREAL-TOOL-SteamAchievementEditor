# 🎮 SteamAchievementEditor

![Unreal
Engine](https://img.shields.io/badge/Unreal%20Engine-5.6%2B-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Tool-Editor%20%26%20Runtime-purple?style=for-the-badge)

------------------------------------------------------------------------

## ✨ Overview

**SteamAchievementEditor** is an Unreal Engine editor tool designed to
**centralize**, **simplify**, and **streamline** the configuration of
**Steam achievements** directly within Unreal Engine.

It provides a clean and efficient workflow to manage achievement
creation, editing, and activation without manually editing configuration
files.

------------------------------------------------------------------------

## 🚀 Features

-   🗂️ Centralized Steam achievement configuration\
-   ✏️ Create and edit achievements directly in the editor\
-   ⚡ One-click apply system\
-   🧹 Automatic handling of bound / unbound achievements\
-   🧠 Designed for clarity and maintainability\
-   📈 Integrated stats workflow (Steam stats editing)

------------------------------------------------------------------------

## 🛠️ Requirements

> ⚠️ **Important**

This tool is compatible only with:

-   **Unreal Engine 5.6 or newer**
-   **Steam Online Subsystem enabled**

Earlier Unreal Engine versions are **not supported**.

------------------------------------------------------------------------

## 🧩 How It Works

### 🎯 Achievements

-   Achievements are created and edited through the
    **SteamAchievementEditor UI** located in:\
    `Tools → Steam Achievement Editor`

-   Clicking **Apply** in the edit window will:

    -   Add the achievement to the generated configuration if it is
        marked as *bound*

-   **Unbound achievements**:

    -   Are **not included** in the configuration file\
    -   Are safely ignored at runtime

-   **Activation**:

    -   Blueprint nodes and C++ async functions are provided\
    -   Uses configured Data Assets for easy integration

------------------------------------------------------------------------

### 📈 Stats

-   Stats are linked to the `AchievementData` object\

-   They can also be used independently via their **API Name**

-   **Activation**:

    -   Blueprint nodes and C++ async functions available\
    -   Fully integrated with the Steam stats system

------------------------------------------------------------------------

## 📂 Configuration Philosophy

The tool was designed with the following goals:

-   ✅ Centralize Unreal-side configuration\
-   ✅ Avoid manual `.ini` edits\
-   ✅ Reduce setup errors\
-   ✅ Improve iteration speed

------------------------------------------------------------------------

## 🧪 Editor-Only Tool

-   The **SteamAchievementEditor** is **editor-only** and has **no
    runtime performance impact**\
-   The **SteamAchievementActivator** affects runtime but simplifies
    achievement usage

All heavy processing is done during configuration and setup.

------------------------------------------------------------------------

## 📌 Notes

-   Steam achievements must still be declared in **Steamworks**
-   Steam stats must still be declared in **Steamworks**
-   This tool handles **Unreal-side configuration only**

------------------------------------------------------------------------

## 📄 License

This project is provided **as-is**.\
You are free to adapt and extend it to fit your workflow.

------------------------------------------------------------------------

## ❤️ Author

Developed with Unreal Engine and Steam integration best practices in
mind.

Happy developing 🚀
