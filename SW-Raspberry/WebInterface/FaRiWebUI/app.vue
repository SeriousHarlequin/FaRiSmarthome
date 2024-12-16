<template>
  <div>
    <NuxtLayout>
      <NuxtPage />
    </NuxtLayout>
  </div>
</template>

<style>
  body {
    background-color: #17153B;
    color: #C8ACD6;
  }
  .dark-mode body {
    background-color: #091a28;
    color: #ebf4f1;
  }
  .sepia-mode body {
    background-color: #f1e7d0;
    color: #433422;
  }

  header {
    background-color: #2E236C;

    margin: 20px 5px;
    
    border: 2px solid #45369b;
    border-radius: 20px;

    padding: 1px 30px;

    display: flex; /* Use flexbox */
    align-items: center; /* Align items vertically */
    }
</style>
