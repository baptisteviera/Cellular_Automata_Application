# Contribuer au projet Cellulut

## Welcome 🍋

:tada: Bienvenue sur le guide de contribution :tada:

Tout ce qui suit constitue l'ensemble des "règles" définies pour s'assurer de produire un code de qualité, compréhensible par tous et facilement gérable.

## Git workflow

We're using Git for versioning our code. If you're unfamiliar with this tool check out this [simple guide](https://rogerdudler.github.io/git-guide/).

Git can be a bit of a pain in the ass sometimes, try to really understand how it works, and when you run into a problem, remember thousands of people had the same problem and that Google is your friend.



Basically : 
- everytime you want to work on something, create a branch from the `master` branch
- add commits
- when you're done working on it, open a **pull request**, and ask for a member of the team to review it.
- discuss and correct what could be wrong on your pull request
- when everything is good, the pull request is merged on master :tada:

## ✅ Good commits 

General rule : **the more the better**

Try to split your work in several commits, it will make sure you follow the baby steps principle: try to have runnable code after each small improvements, it helps you keep track of your progress and ensure you don't try to fix too many things at the same time.

Your commits should always start with the prefixes, the following table tells you what prefixes to use:

**Prefix** | **Description**
--- | ---
`feat` | When you are working on a new feature request. Used to identify which branches contain which features.
`fix` | Fixes, both major and minor ones, are attributed with this prefix to identify what was fixed and where.
`app`| You're working on something relevant to the front-end
`api`| You're working on something relevant to the back-end

### Examples

```
- component/container.tsx
```
> Message: "[feat][app] modify container component to reflect new design"
```
- pages/home.ts
```
> Message: "[feat][app] update Home page to enable new feature."
```
- util/theme-util.js
```
> Message: "[feat][app] color add a new util function to get compliment colors."
```
- util/header-util.js
```
> Message: "[feat][app] new button in header for parsing and created a util."

## ❌ Bad Committing 

```
- pages/home.js
- component/container.jsx
- util/theme-util.js
- util/header-util.js
```
> Message: "Changes"
