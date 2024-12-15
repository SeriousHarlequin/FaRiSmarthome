<template>
    <div>
        <AppHeader />
        <div id="Page">
            <slot />
        </div>
        <AppFooter />
    </div>
</template>

<style>
    #Page {
        display: flex;
        justify-content: center; /* Center horizontally */
        height: 100vh; /* Full viewport height */
    }
</style>