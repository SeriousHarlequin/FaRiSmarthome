<template>
    <div id="Page">
        <h1>Hello World</h1>
        <p v-if="error">Error: {{ error.message }}</p>
        <p v-else>Data: {{ ledState }}</p>
    </div>
</template>

<script setup lang="ts">
    const { data: ledState, error } = await useFetch('http://192.168.10.84/fetch')
</script>