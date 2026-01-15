# 🎮 SteamAchievementEditor

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.6%2B-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Tool-Editor%20Only-purple?style=for-the-badge)

---

## ✨ Overview

![SteamAchievementEditor Preview](https://via.placeholder.com/800x200?text=SteamAchievementEditor+Preview)

**SteamAchievementEditor** is an Unreal Engine editor tool designed to **centralize**, **simplify**, and **streamline** the configuration of **Steam achievements** directly on the Unreal side.

The tool provides a clean and efficient workflow to manage achievement creation, editing, and activation without manually handling configuration files.

---

## 🚀 Features

* 🗂️ Centralized Steam achievement configuration
* ✏️ Create and edit achievements directly in-editor
* ⚡ One-click apply system
* 🧹 Automatic handling of bound / unbound achievements
* 🧠 Designed for clarity and maintainability

---

## 🛠️ Requirements

> ⚠️ **Important**

This tool is compatible **only** with:

* **Unreal Engine 5.6 or newer**
* **Steam Online Subsystem** enabled

Earlier Unreal Engine versions are **not supported**.

---

## 🧩 How It Works

* Achievements are created and edited through the **SteamAchievementEditor UI**

* Clicking **Apply** will:

  * Add it to the generated configuration if set to binded to it.

* Unbound achievements:

  * Will **not** appear in the configuration file
  * Are ignored safely at runtime

* Ease activation:

  * Functional BP Node and C++ Async to use with the configurated data Assets

This ensures a clean and reliable setup aligned with Steam requirements.

---

## 📂 Configuration Philosophy

The SteamAchievementEditor was built with the following goals in mind:

* ✅ Keep Unreal-side configuration centralized
* ✅ Avoid manual `.ini` edits
* ✅ Reduce setup errors
* ✅ Improve iteration speed

---

## 🧪 Editor-Only Tool

This tool is **Editor-only** and does not impact runtime performance.
All processing is done during configuration and setup.

---

## 📌 Notes

* Steam achievements must still be declared on the **Steamworks** side
* This tool handles **Unreal-side configuration only**

---

## 📄 License

This project is provided as-is. Feel free to adapt and extend it to fit your workflow.

---

## ❤️ Author

Developed with Unreal Engine and Steam integration best practices in mind.

Happy developing 🚀
