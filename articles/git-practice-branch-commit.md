# git practice branch & commits





```bash
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]


feat(user-profile)!: Add user profile page and API integration

This commit adds a new user profile page that displays the user's information and allows them to update their profile. It also includes the necessary API integration to fetch and update the user data.

Closes #123
BREAKING CHANGE: The API endpoint /users has been removed. Use /profiles instead.
```

**Type**: `fix`, `feat`, `docs`, `style`,`refactor`, `test`, `perf`, `build`, `ci`, `chore`

- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation updates
- `style`: Changes that do not affect the meaning of the code (e.g., whitespace, formatting, etc.)
- `refactor`: Code changes that neither fix a bug nor add a feature
- `perf`: Performance improvements
- `test`: Adding or updating tests
- `build`: Changes to the build system or external dependencies
- `ci`: Changes to the continuous integration configuration
- `chore`: Miscellaneous tasks that do not modify the source code or test files

**optional scope**: for flexible content provide extent the info of <type> like `feat(auth)`, `fix(login)`

**description**:  

- The commit message should be written in the imperative, present tense.

  > e.g., "Add feature" instead of "Added feature" or "Adds feature".

- The first line of the commit message (the subject) should be concise and limited to 50 characters.

-  An optional longer description**(optional body)** can be added after the subject, separated by a blank line. This description should provide more context and details about the changes made.

**footers**: `Closes`, `Fixes`, `BREAKING CHANGE`, `Deprecates`

used to provide additional information about the commit, such as references to related issues or pull requests, breaking changes, or deprecations.

