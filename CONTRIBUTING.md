# For contributors
## Tech Stack
The entire package has been made using C/C++.
You need to have a GCC compiler with a **version** higher than 10.2.0.
### Windows Users
You can get an updated  version of GCC from [Winlibs](https://winlibs.com/)

## Issues for new contributors
While we welcome any form of contribution, we've marked a few issues which are particularly suited for new contributors. These issues are marked with the `good first issue` label. Other issues are also marked according to their difficulty level.

## How to contribute
If you would like to work on an issue, please follow these guidelines:
* Ask one of the maintainers to assign the issue to you, and feel free to ask any questions to clarify the issue
* Fork this repository to your GitHub account by clicking on the 'Fork' button at the top-right of the page
* Clone your fork of the repository to your local machine
* Enter the directory of the repository, and follow the installation instructions given in the README
* Create a new branch to hold your changes, and name your branches according to the issue you're working on

`git checkout -b your-new-branch-name`

* Make your changes to the code and try to resolve the issue. Make sure you add descriptive comments and variable names, so that it becomes easier for everyone else to understand your code
* Now, stage your changes with

`git add .`

* Commit your changes, and ensure that your commit message describes the changes you have made in your code. Commit messages should preferably be in the imperative mood, such as "add documentation" or "modify README" instead of in the past tense. You can commit your changes and add a message by running

`git commit -m "your commit message goes here"`

* That's all! Now, you just need to push your changes to your repository with

`git push -u origin your-new-branch-name`

## Adding Features
Each feature must be created in a separate header (.hpp) file. The main CLI code is in [compressor.cpp](https://github.com/DebadityaPal/k-means-compressor/blob/ead70947cf5630fd6d786001538600ecdeaba800/compressor.cpp), 
Every time a new feature is added, add the relevant arguments to this file.

## Opening a pull request
If you're working on an issue, and would like to submit a pull request, please follow these guidelines:
* Visit your fork of the repository, and click on the 'Pull Request' button that would be appearing on top of the page
* Mention the changes in the PR in the title briefly
* Mention the issue number that this PR will resolve in the description so as to automatically close the issue when the PR is merged
* Describe your changes in the PR description, and feel free to give examples or code samples
* If you would like to continue working on your PR, and mark it as a work in progress, you can submit a draft PR instead

## Linter
Currently we are using Intellisense C++ Linter, it should be auto installed for VSCode users if the C/C++ extension has been installed.
