// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  compatibilityDate: '2024-11-01',
  devtools: { enabled: true },
  modules: ['@nuxtjs/color-mode'],
  colorMode: {
    preference: 'system', // default value of $colorMode.preference
    fallback: 'light', // fallback value if not system preference found
    hid: 'nuxt-color-mode-script',
    globalName: '__NUXT_COLOR_MODE__',
    componentName: 'ColorScheme',
    classPrefix: '',
    classSuffix: '-mode',
    storage: 'localStorage', // or 'sessionStorage' or 'cookie'farismart
    storageKey: 'nuxt-color-mode'
  },
  // nitro: {
  //   serverHandlers: [
  //     {
  //       route: '/fetchTemp',
  //       handler: '~/server/middleware/proxy.js'
  //     }
  //   ]
  // }
  

})

//run to setup:
