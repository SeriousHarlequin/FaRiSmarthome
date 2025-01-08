<template>
    <div id="Page">
        <h1>Hello World</h1>
        <!-- <p v-if="loading">Loading...</p>
        <p v-else-if="error">Error: {{ error.message }}</p>
        <p v-else>Data: {{ temperature }}</p> -->
        <p>Data: {{ temperature }}</p>
    </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'

const temperature = ref(null)

onMounted(async () => {
    temperature.value = await $fetch('http://192.168.143.28/fetchTemp')
})
</script>

<!-- <script setup lang="ts">
const { data: temperature, error } = await useFetch('http://192.168.143.28/fetchTemp')
</script> -->