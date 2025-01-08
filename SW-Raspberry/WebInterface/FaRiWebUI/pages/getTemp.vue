<template>
    <div>
        <h1>Hello World</h1>
        <p v-if="temperature !== null">Data: {{ temperature }}</p>
        <p v-else>Loading...</p>
    </div>

</template>

<script setup>
    import { ref, onMounted } from 'vue'

    var temperature = ref(null)

    onMounted(async () => {
        try {
            const { data } = await fetch('http://192.168.143.28/fetchTemp')
            temperature.value = data.value
        } catch (error) {
            console.error('Error fetching temperature:', error)
        }
    })
</script>