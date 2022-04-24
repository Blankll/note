### use @testing-library/react to test react-modal click overlay to close dialog

```tsx
// @ts-ignore
fireEvent.click(document.querySelector(".ReactModal__Overlay"));
await new Promise((resolve) => setTimeout(resolve, 0));
expect(...).not.toBeInTheDocument();
```