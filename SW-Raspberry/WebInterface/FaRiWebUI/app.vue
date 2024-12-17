<template>
  <div>
    <NuxtLayout>
      <NuxtPage />
    </NuxtLayout>
  </div>
</template>

<script>
  import '~/colorModes.css'
</script>

<style>
  header {
    position: sticky;
    top: 0;
    left: 0;
    width: 100%;
    box-sizing: border-box;
    
    border: 2px solid;
    border-radius: 20px;

    padding: 1px 30px;

    display: flex; /* Use flexbox */
    align-items: center; /* Align items vertically */
}
  footer {
    margin: 0px -7px;

    border-top: 2px solid;

    padding: 1px 30px;

    display: flex; /* Use flexbox */
    align-items: center; /* Align items vertically */
  }
  select {
    border-style: solid;
    border-width: 2px;
  }
</style>