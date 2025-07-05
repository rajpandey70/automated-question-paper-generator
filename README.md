# automated-question-paper-generator
# 📝 Automated Question Paper Generator (C++ | DSA Project)

## 📌 Overview
The **Automated Question Paper Generator** is a console-based C++ project that dynamically generates a question paper based on user-defined criteria like total marks, topic(s), and difficulty level. It uses **Data Structures & Algorithms (DSA)** concepts to filter and select appropriate questions from a large question bank.

## 🚀 Key Features
- 📁 Loads questions from an external text file  
- 🧠 Filters by topic(s) – supports multiple comma-separated topics  
- 🎯 Filters by difficulty – Easy (1), Medium (2), Hard (3), or Mix  
- 📊 Marks-based generation – Enter total marks and get a best-fit paper  
- 🧮 Subset algorithm used to match target marks efficiently  
- 📝 Generates a formatted text output in `output/GeneratedPaper.txt`  
- 🎓 Includes institutional header, instructions, and neat formatting

## ⚙️ How It Works
1. All questions are loaded from `questions.txt`, formatted as:
   ```
   ID|Question Text|Topic|Difficulty|Marks
   ```
2. The user provides:
   - Total marks (e.g., 60)
   - Difficulty (e.g., 1,2 for Easy+Medium)
   - Topic(s) (e.g., arrays,recursion,dp)
3. The system filters relevant questions and uses a **brute-force subset algorithm** to select the best combination up to the required marks.
4. The question paper is saved in a structured layout with:
   - University header
   - Subject, date, timing
   - List of selected questions with marks

## 🧠 DSA Concepts Used
- `struct` for managing question records  
- `vector` for dynamic storage of question sets  
- `set` for efficient topic filtering  
- Bitmask/subset generation to maximize marks match  
- String algorithms for input parsing and normalization  
- Brute-force + greedy selection logic

## 📂 File Structure
```
main.cpp             // Main application logic
generator.cpp        // Core functions (load, filter, select, save)
generator.h          // Struct & function declarations
questions.txt        // Question bank (editable by user)
output/GeneratedPaper.txt // Final output file
```

## 🧪 Sample Usage
```
Enter total marks for the paper: 60
Enter difficulty (0=Any, 1=Easy, 2=Medium, 3=Hard): 2,3
Enter topic name(s): arrays,recursion
Enter subject name: Data Structures
Enter exam date (DD-MM-YYYY): 05-07-2025
```

## ✅ Output
Generates a paper with the exact or closest possible mark total with clean formatting.

## 📚 Future Enhancements
- Export to PDF
- GUI Interface (QT or Web frontend)
- Section-wise generation (e.g., A, B, C)
- Question type tagging (MCQ, Theory, etc.)
- Admin panel to add/edit questions interactively
